pdfDumpInfoDict(char const* fname)
{
    try
    {
	QPDF pdf;
	pdf.processFile(fname);
	dumpInfoDict(pdf);
    }
    catch (std::exception& e)
    {
	std::cerr << e.what() << std::endl;
	exit(2);
    }
}
