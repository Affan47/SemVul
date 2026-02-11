get_authorized_princ_names(luser, cmd, princ_list)
    const char *luser;
    char *cmd;
    char ***princ_list;
{

    struct passwd *pwd;
    int k5login_flag =0;
    int k5users_flag =0;
    FILE * login_fp = NULL , * users_fp = NULL;
    char **  k5login_list = NULL, ** k5users_list = NULL;
    char ** k5users_filt_list = NULL;
    char ** combined_list = NULL;
    struct stat tb;
    krb5_error_code retval;

    *princ_list = NULL;


    if ((pwd = getpwnam(luser)) == NULL)
        return 0;

    k5login_flag = stat(k5login_path, &tb);
    k5users_flag = stat(k5users_path, &tb);

    if (!k5login_flag){
        if ((login_fp = fopen(k5login_path, "r")) == NULL)
            return 0;
        if ( fowner(login_fp, pwd->pw_uid) == FALSE){
            close_time(1 , (FILE *) 0 ,
                       k5login_flag,login_fp);
            return 0;
        }
    }
    if (!k5users_flag){
        if ((users_fp = fopen(k5users_path, "r")) == NULL)
            return 0;

        if ( fowner(users_fp, pwd->pw_uid) == FALSE){
            close_time(k5users_flag,users_fp, k5login_flag,login_fp);
            return 0;
        }

        retval = get_all_princ_from_file (users_fp, &k5users_list);
        if(retval) {
            close_time(k5users_flag,users_fp, k5login_flag,login_fp);
            return retval;
        }

        rewind(users_fp);

        retval = filter(users_fp,cmd, k5users_list, &k5users_filt_list);
        if(retval) {
            close_time(k5users_flag,users_fp, k5login_flag, login_fp);
            return retval;
        }
    }

    if (!k5login_flag){
        retval = get_all_princ_from_file (login_fp, &k5login_list);
        if(retval) {
            close_time(k5users_flag,users_fp, k5login_flag,login_fp);
            return retval;
        }
    }

    close_time(k5users_flag,users_fp, k5login_flag, login_fp);

    if (cmd) {
        retval = list_union(k5login_list, k5users_filt_list, &combined_list);
        if (retval){
            close_time(k5users_flag,users_fp, k5login_flag,login_fp);
            return retval;
        }
        *princ_list = combined_list;
        return 0;
    } else {
        if (k5users_filt_list != NULL)
            free(k5users_filt_list);
        *princ_list = k5login_list;
        return 0;
    }
}
