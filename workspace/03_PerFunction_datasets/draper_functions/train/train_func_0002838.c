libfat_determine_fattype(Volume_t *V) {
    int res;
    off_t fsi_offset;
    char type[9];

    sprintf(type,"FAT12   ");
    if ((res = memcmp( (char *) &(((char *) &(V->Bpb))[54]), type, 8)) == 0) { V->FatType = FAT12; fprintf(stderr,"fat type: FAT12\n"); return 0; }
    sprintf(type,"FAT16   ");
    if ((res = memcmp( (char *) &(((char *) &(V->Bpb))[54]), type, 8)) == 0) { V->FatType = FAT16; fprintf(stderr,"fat type: FAT16\n");return 0; }
    sprintf(type,"FAT32   ");
    if ((res = memcmp( (char *) V->Bpb.BS_FilSysType, type, 8)) == 0) {

		fprintf(stderr,"fat type: FAT32. Fsi at %u\n",EFW(V->Bpb.BPB_FSInfo));
        V->FatType = FAT32;
        fsi_offset = EFW(V->Bpb.BPB_FSInfo) * EFW(V->Bpb.BPB_BytsPerSec);

		fprintf(stderr,"Fsioff: %d, size: %d\n",(int) fsi_offset, sizeof(FSInfo_t));
        if ( (res = lseek(V->blkDevFd, fsi_offset, SEEK_SET)) != fsi_offset ) { perror("FSI lseek() error"); return -1; }
        if ( (res = readn(V->blkDevFd, &(V->Fsi), sizeof(FSInfo_t))) != sizeof(FSInfo_t) ) { perror("FSI readn() error"); return -1; }
		fprintf(stderr,"--- nxtfree --- :%u\n",EFD(V->Fsi.FSI_Nxt_Free));
		fprintf(stderr,"--- freecnt --- :%u\n",EFD(V->Fsi.FSI_Free_Count));
		fflush(stderr);
        return 0;
    }

    return -1;


}
