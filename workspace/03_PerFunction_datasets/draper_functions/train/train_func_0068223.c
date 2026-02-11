krb5_ktfileint_find_slot(krb5_context context, krb5_keytab id, krb5_int32 *size_needed, krb5_int32 *commit_point_ptr)
{
    FILE *fp;
    krb5_int32 size, zero_point, commit_point;
    krb5_kt_vno kt_vno;

    KTCHECKLOCK(id);
    fp = KTFILEP(id);

    if (fseek(fp, 0, SEEK_SET))
        return errno;
    if (!fread(&kt_vno, sizeof(kt_vno), 1, fp))
        return errno;

    for (;;) {
        commit_point = ftell(fp);
        if (commit_point == -1)
            return errno;
        if (!fread(&size, sizeof(size), 1, fp)) {


            if (fseek(fp, 0, SEEK_CUR))
                return errno;

            size = 0;
            if (!fwrite(&size, sizeof(size), 1, fp))
                return errno;
            break;
        }

        if (KTVERSION(id) != KRB5_KT_VNO_1)
            size = ntohl(size);

        if (size > 0) {

            if (fseek(fp, size, SEEK_CUR))
                return errno;
        } else if (size < 0) {

            size = -size;
            if (size >= *size_needed) {
                *size_needed = size;
                break;
            } else {
                if (fseek(fp, size, SEEK_CUR))
                    return errno;
            }
        } else {


            zero_point = ftell(fp);
            if (zero_point == -1)
                return errno;
            if (fseek(fp, *size_needed, SEEK_CUR))
                return errno;

            if (!fwrite(&size, sizeof(size), 1, fp))
                return errno;
            if (fseek(fp, zero_point, SEEK_SET))
                return errno;
            break;
        }
    }

    *commit_point_ptr = commit_point;
    return 0;
}
