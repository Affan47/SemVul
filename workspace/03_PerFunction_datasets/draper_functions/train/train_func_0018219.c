main(void)
{
    herr_t err;
    herr_t num_errors = 0;


    fileID = H5Fcreate(TEST_FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if(fileID <0)
    {
        fprintf(stderr, "Couldn't create file.\n");
        num_errors = 1;
    }
    else {

            num_errors += BasicTest();

            num_errors += TestCompoundDatatype();

            num_errors += TestGetPacket();

            num_errors += TestGetNext();

            num_errors += TestCompress();

            num_errors += TestErrors();

            num_errors += SystemTest();

#ifdef VLPT_REMOVED
            num_errors += VariableLengthTest();
#endif


        err = H5Fclose(fileID);
        if( err < 0 )
        {
            fprintf(stderr, "Failed to close file.\n");
            num_errors++;
        }


        remove(TEST_FILE);
    }

    if (num_errors == 0)

      return 0;
    else

      return -1;
}
