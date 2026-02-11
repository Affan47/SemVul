external_link_path(hid_t fapl, hbool_t new_format)
{
    hid_t	fid = (-1);
    hid_t	gid = (-1), gid2 = (-1);
    char        objname[NAME_BUF_SIZE];
    char	filename1[NAME_BUF_SIZE];
    char	filename2[NAME_BUF_SIZE];

    if(new_format)
        TESTING("external link to object on path (w/new group format)")
    else
        TESTING("external link to object on path")


    h5_fixname(FILENAME[3], fapl, filename1, sizeof filename1);
    h5_fixname(FILENAME[4], fapl, filename2, sizeof filename2);


    if((fid=H5Fcreate(filename1, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0) TEST_ERROR


    if((gid = H5Gcreate2(fid, "A", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) TEST_ERROR
    if(H5Gclose(gid) < 0) TEST_ERROR

    if((gid = H5Gcreate2(fid, "A/B", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) TEST_ERROR
    if(H5Gclose(gid) < 0) TEST_ERROR

    if((gid = H5Gcreate2(fid, "A/B/C", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) TEST_ERROR
    if(H5Gclose(gid) < 0) TEST_ERROR


    if(H5Fclose(fid) < 0) TEST_ERROR


    if((fid=H5Fcreate(filename2, H5F_ACC_TRUNC, H5P_DEFAULT, fapl)) < 0) TEST_ERROR


    if(H5Lcreate_external(filename1, "/A/B/C", fid, "ext_link", H5P_DEFAULT, H5P_DEFAULT) < 0) TEST_ERROR


    if((gid = H5Gopen2(fid, "ext_link", H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    if(H5Iget_name(gid, objname, (size_t)NAME_BUF_SIZE) < 0) TEST_ERROR
    if(HDstrcmp(objname, "/A/B/C")) TEST_ERROR


    if((gid2 = H5Gcreate2(gid, "new_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) TEST_ERROR


    if(H5Gclose(gid2) < 0) TEST_ERROR


    if(H5Gclose(gid) < 0) TEST_ERROR


    if(H5Fclose(fid) < 0) TEST_ERROR


    if((fid = H5Fopen(filename1, H5F_ACC_RDONLY, fapl)) < 0) TEST_ERROR


    if((gid = H5Gopen2(fid, "/A/B/C/new_group", H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    if(H5Iget_name(gid, objname, (size_t)NAME_BUF_SIZE) < 0) TEST_ERROR
    if(HDstrcmp(objname, "/A/B/C/new_group")) TEST_ERROR


    if(H5Gclose(gid) < 0) TEST_ERROR


    if(H5Fclose(fid) < 0) TEST_ERROR


    PASSED();
    return 0;

 error:
    H5E_BEGIN_TRY {
    	H5Gclose (gid2);
    	H5Gclose (gid);
    	H5Fclose (fid);
    } H5E_END_TRY;
    return -1;
}
