zzip_compr_str(int compr)
{
    switch (compr)
    {

    case ZZIP_IS_STORED:		return "stored";
    case ZZIP_IS_SHRUNK:		return "shrunk";
    case ZZIP_IS_REDUCEDx1:
    case ZZIP_IS_REDUCEDx2:
    case ZZIP_IS_REDUCEDx3:
    case ZZIP_IS_REDUCEDx4:		return "reduced";
    case ZZIP_IS_IMPLODED:		return "imploded";
    case ZZIP_IS_TOKENIZED:		return "tokenized";
    case ZZIP_IS_DEFLATED:		return "deflated";
    case ZZIP_IS_DEFLATED_BETTER:	return "deflatedX";
    case ZZIP_IS_IMPLODED_BETTER:	return "implodedX";
    default:
        if (0 < compr && compr < 256)   return "zipped";
        else
        {
#	ifdef S_ISDIR
            if (S_ISDIR(compr))		return "directory";
#	endif
#	ifdef S_ISCHR
            if (S_ISCHR(compr))		return "is/chr";
#	endif
#	ifdef S_ISBLK
            if (S_ISBLK(compr))		return "is/blk";
#	endif
#	ifdef S_ISFIFO
            if (S_ISFIFO(compr))	return "is/fifo";
#	endif
#	ifdef S_ISSOCK
            if (S_ISSOCK(compr))	return "is/sock";
#	endif
#	ifdef S_ISLNK
            if (S_ISLNK(compr))		return "is/lnk";
#	endif
            return "special";
        }

    }
}
