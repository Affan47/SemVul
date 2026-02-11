__ecereNameSpace__ecere__gfx__bitmaps__JPEG_SkipInputData(j_decompress_ptr cinfo, long num_bytes)
{
SourceManager * src = (SourceManager *)(*cinfo).src;

if(num_bytes > 0)
{
while(num_bytes > (long)(*src).pub.bytes_in_buffer)
{
num_bytes -= (long)(*src).pub.bytes_in_buffer;
__ecereNameSpace__ecere__gfx__bitmaps__JPEG_FillInputBuffer(cinfo);
}
(*src).pub.next_input_byte += (unsigned int)num_bytes;
(*src).pub.bytes_in_buffer -= (unsigned int)num_bytes;
}
}
