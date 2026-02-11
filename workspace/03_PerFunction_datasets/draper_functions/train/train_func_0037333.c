qpdf_get_buffer_length(qpdf_data qpdf)
{
    qpdf_get_buffer_internal(qpdf);
    size_t result = 0;
    if (qpdf->output_buffer)
    {
	result = qpdf->output_buffer->getSize();
    }
    return result;
}
