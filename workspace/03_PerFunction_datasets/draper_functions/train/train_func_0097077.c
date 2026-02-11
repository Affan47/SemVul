test_one(hid_t file)
{
    hid_t	work = -1, grp = -1;
    herr_t	status;


    if((work = H5Gcreate2(file, "/test_one", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR


    TESTING("unlink by absolute name");
    if((grp = H5Gcreate2(work, "foo", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    if(H5Gclose(grp) < 0) FAIL_STACK_ERROR
    if(H5Ldelete(file, "/test_one/foo", H5P_DEFAULT) < 0) FAIL_STACK_ERROR
    PASSED();


    TESTING("unlink by local name");
    if((grp = H5Gcreate2(work, "foo", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    if(H5Gclose(grp) < 0) FAIL_STACK_ERROR
    if(H5Ldelete(work, "foo", H5P_DEFAULT) < 0) FAIL_STACK_ERROR
    PASSED();


    TESTING("unlink without a name");
    if((grp = H5Gcreate2(work, "foo", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT)) < 0) FAIL_STACK_ERROR
    H5E_BEGIN_TRY {
	status = H5Ldelete(grp, ".", H5P_DEFAULT);
    } H5E_END_TRY;
    if(status>=0)
	FAIL_PUTS_ERROR("    Unlinking object w/o a name should have failed.")
    if(H5Gclose(grp) < 0) FAIL_STACK_ERROR


    if(H5Gclose(work) < 0) FAIL_STACK_ERROR

    PASSED();
    return 0;

 error:
    H5E_BEGIN_TRY {
	H5Gclose(work);
	H5Gclose(grp);
    } H5E_END_TRY;
    return 1;
}
