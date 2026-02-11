handle_links(hid_t fid, const char *links, void UNUSED * data, int UNUSED pe, const char UNUSED *display_name)
{
    H5L_info_t linfo;

    if(H5Lget_info(fid, links, &linfo, H5P_DEFAULT) < 0) {
        error_msg("unable to get link info from \"%s\"\n", links);
        h5tools_setstatus(EXIT_FAILURE);
    }
    else if(linfo.type == H5L_TYPE_HARD) {
        error_msg("\"%s\" is a hard link\n", links);
        h5tools_setstatus(EXIT_FAILURE);
    }
    else {
        char *buf = (char *)HDmalloc(linfo.u.val_size);
        PRINTVALSTREAM(rawoutstream, "\n");

        switch(linfo.type) {
        case H5L_TYPE_SOFT:
            begin_obj(h5tools_dump_header_format->softlinkbegin, links, h5tools_dump_header_format->softlinkblockbegin);
            PRINTVALSTREAM(rawoutstream, "\n");
            indentation(COL);
            if(H5Lget_val(fid, links, buf, linfo.u.val_size, H5P_DEFAULT) >= 0)
                PRINTSTREAM(rawoutstream, "LINKTARGET \"%s\"\n", buf);
            else {
                error_msg("h5dump error: unable to get link value for \"%s\"\n", links);
                h5tools_setstatus(EXIT_FAILURE);
            }
            end_obj(h5tools_dump_header_format->softlinkend, h5tools_dump_header_format->softlinkblockend);
            break;

        case H5L_TYPE_EXTERNAL:
            begin_obj(h5tools_dump_header_format->udlinkbegin, links, h5tools_dump_header_format->udlinkblockbegin);
            PRINTVALSTREAM(rawoutstream, "\n");
            indentation(COL);
            begin_obj(h5tools_dump_header_format->extlinkbegin, links, h5tools_dump_header_format->extlinkblockbegin);
            PRINTVALSTREAM(rawoutstream, "\n");
            if(H5Lget_val(fid, links, buf, linfo.u.val_size, H5P_DEFAULT) >= 0) {
                const char *elink_file;
                const char *elink_path;

                if(H5Lunpack_elink_val(buf, linfo.u.val_size, NULL, &elink_file, &elink_path)>=0) {
                    indentation(COL);
                    PRINTSTREAM(rawoutstream, "LINKCLASS %d\n", linfo.type);
                    indentation(COL);
                    PRINTSTREAM(rawoutstream, "TARGETFILE \"%s\"\n", elink_file);
                    indentation(COL);
                    PRINTSTREAM(rawoutstream, "TARGETPATH \"%s\"\n", elink_path);
                }
                else {
                    error_msg("h5dump error: unable to unpack external link value for \"%s\"\n", links);
                    h5tools_setstatus(EXIT_FAILURE);
                }
            }
            else {
                error_msg("h5dump error: unable to get external link value for \"%s\"\n", links);
                h5tools_setstatus(EXIT_FAILURE);
            }
            end_obj(h5tools_dump_header_format->extlinkend, h5tools_dump_header_format->extlinkblockend);
            break;

        default:
            begin_obj(h5tools_dump_header_format->udlinkbegin, links, h5tools_dump_header_format->udlinkblockbegin);
            PRINTVALSTREAM(rawoutstream, "\n");
            indentation(COL);
            begin_obj(h5tools_dump_header_format->udlinkbegin, links, h5tools_dump_header_format->udlinkblockbegin);
            PRINTVALSTREAM(rawoutstream, "\n");
            indentation(COL);
            PRINTSTREAM(rawoutstream, "LINKCLASS %d\n", linfo.type);
            end_obj(h5tools_dump_header_format->udlinkend, h5tools_dump_header_format->udlinkblockend);
            break;
        }
        HDfree(buf);
    }
}
