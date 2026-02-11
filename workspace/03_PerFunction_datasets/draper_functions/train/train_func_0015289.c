call_init_write(qpdf_data qpdf)
{
    qpdf->qpdf_writer = new QPDFWriter(*(qpdf->qpdf), qpdf->filename);
}
