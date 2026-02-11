vzt_wr_set_compression_type(struct vzt_wr_trace *lt, unsigned int type)
{
if(lt)
	{
	if((type == VZT_WR_IS_GZ) || (type == VZT_WR_IS_BZ2) || (type == VZT_WR_IS_LZMA))
		{
		lt->ztype_cfg = type;
		}
	}
}
