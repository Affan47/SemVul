hfsplus_fetch_node (cli_ctx *ctx, hfsPlusVolumeHeader *volHeader, hfsHeaderRecord *catHeader,
    hfsHeaderRecord *extHeader, uint32_t node, uint8_t *buff)
{
    int foundBlock = 0;
    uint64_t catalogOffset;
    uint32_t fetchBlock, fetchStart;
    uint32_t extentNum = 0, realFileBlock;
    size_t fileOffset = 0;
    hfsPlusForkData *catFork;

    UNUSEDPARAM(extHeader);


    if (node >= catHeader->totalNodes) {
        cli_dbgmsg("hfsplus_fetch_node: invalid node number " STDu32 "\n", node);
        return CL_EFORMAT;
    }

    catFork = &(volHeader->catalogFile);

    if (catHeader->nodeSize <= volHeader->blockSize) {


        catalogOffset = (uint64_t)node * catHeader->nodeSize;

        fetchBlock = (uint32_t) (catalogOffset / volHeader->blockSize);
        fetchStart = (uint32_t) (catalogOffset % volHeader->blockSize);
        cli_dbgmsg("hfsplus_fetch_node: need catalog block " STDu32 "\n", fetchBlock);
        if (fetchBlock >= catFork->totalBlocks) {
            cli_dbgmsg("hfsplus_fetch_node: block number invalid!\n");
            return CL_EFORMAT;
        }


        for (extentNum = 0; extentNum < 8; extentNum++) {
            hfsPlusExtentDescriptor *currExt = &(catFork->extents[extentNum]);


            if ((currExt->startBlock == 0) || (currExt->blockCount == 0)) {
                cli_dbgmsg("hfsplus_fetch_node: extent " STDu32 " empty!\n", extentNum);
                return CL_EFORMAT;
            }

            if ((currExt->startBlock & 0x10000000) && (currExt->blockCount & 0x10000000)) {
                cli_dbgmsg("hfsplus_fetch_node: extent " STDu32 " illegal!\n", extentNum);
                return CL_EFORMAT;
            }

            if (fetchBlock < currExt->blockCount) {
                cli_dbgmsg("hfsplus_fetch_node: found block in extent " STDu32 "\n", extentNum);
                realFileBlock = currExt->startBlock + fetchBlock;
                foundBlock = 1;
                break;
            }
            else {
                cli_dbgmsg("hfsplus_fetch_node: not in extent " STDu32 "\n", extentNum);
                fetchBlock -= currExt->blockCount;
            }
        }

        if (foundBlock == 0) {
            cli_dbgmsg("hfsplus_fetch_node: not in first 8 extents\n");
            cli_dbgmsg("hfsplus_fetch_node: finding this node requires extent overflow support\n");
            return CL_EFORMAT;
        }


        if (realFileBlock >= volHeader->totalBlocks) {
            cli_dbgmsg("hfsplus_fetch_node: block past end of volume\n");
            return CL_EFORMAT;
        }
        fileOffset = realFileBlock * volHeader->blockSize;
    }
    else {

        cli_dbgmsg("hfsplus_fetch_node: nodesize bigger than blocksize, is this allowed?\n");
        return CL_EFORMAT;
    }

    if (fileOffset) {
        if (fmap_readn(*ctx->fmap, buff, fileOffset, catHeader->nodeSize) != catHeader->nodeSize) {
            cli_dbgmsg("hfsplus_fetch_node: not all bytes read\n");
            return CL_EFORMAT;
        }
    }
    else {
        cli_dbgmsg("hfsplus_fetch_node: nodesize bigger than blocksize, is this allowed?\n");
        return CL_EFORMAT;
    }

    return CL_CLEAN;
}
