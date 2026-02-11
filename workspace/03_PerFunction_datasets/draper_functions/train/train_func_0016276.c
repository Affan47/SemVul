test_h5s_compound_scalar_read()
{
    hsize_t		tdims[4];


    SUBTEST("Compound Dataspace Reading");
    try {

	H5File fid1(DATAFILE, H5F_ACC_RDWR);


	DataSet dataset = fid1.openDataSet("Dataset1");

	DataSpace sid1 = dataset.getSpace();


	hssize_t n = sid1.getSimpleExtentNpoints();
	verify_val((long)n, 1, "DataSpace::getSimpleExtentNpoints", __LINE__, __FILE__);


	int ndims = sid1.getSimpleExtentNdims();
	verify_val(ndims, SPACE3_RANK, "DataSpace::getSimpleExtentNdims", __LINE__, __FILE__);

	ndims = sid1.getSimpleExtentDims(tdims);
	verify_val(ndims, 0, "DataSpace::getSimpleExtentDims", __LINE__, __FILE__);


	CompType type(dataset);

	struct space4_struct rdata;
	dataset.read(&rdata, type);


	if(HDmemcmp(&space4_data,&rdata,sizeof(struct space4_struct)))
	{
            cerr << "scalar data different: space4_data.c1="
		<< space4_data.c1 << ", read_data4.c1=" << rdata.c1 << endl;
            cerr << "scalar data different: space4_data.u="
		<< space4_data.u << ", read_data4.u=" << rdata.u << endl;
            cerr << "scalar data different: space4_data.f="
		<< space4_data.f << ", read_data4.f=" << rdata.f << endl;
            TestErrPrintf("scalar data different: space4_data.c1=%c, read_data4.c1=%c\n",
		space4_data.c1, rdata.c2);
	}
	PASSED();
    }
    catch (Exception E)
    {

	issue_fail_msg("test_h5s_compound_scalar_read()", __LINE__, __FILE__, E.getCDetailMsg());
    }
}
