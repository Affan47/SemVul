buffered_image_get_row(stp_image_t* image,unsigned char *data, size_t byte_limit, int row)
{
	struct buffered_image_priv *priv = image->rep;
	int width = buffered_image_width(image);
	int height = buffered_image_height(image);

	int bytes_per_pixel = byte_limit / width;
	int inc = bytes_per_pixel;
	unsigned char* src;
	int i;

	if(!priv->buf){
		priv->buf = stp_zalloc((sizeof(unsigned short*) + 1) * height);
		if(!priv->buf){
			return STP_IMAGE_STATUS_ABORT;
		}
		for(i=0;i<height;i++){
			priv->buf[i] = stp_malloc(byte_limit);
			if(STP_IMAGE_STATUS_OK != priv->image->get_row(priv->image,priv->buf[i],byte_limit,i))
				return STP_IMAGE_STATUS_ABORT;
		}
	}
	if(priv->flags & BUFFER_FLAG_FLIP_Y)
		row = height - row - 1;

	src = priv->buf[row];

	if(priv->flags & BUFFER_FLAG_FLIP_X){
		src += byte_limit - bytes_per_pixel;
		inc = -bytes_per_pixel;
	}


	for( i = 0 ; i < width ; i++){
		memcpy(data,src,bytes_per_pixel);
		src += inc;
		data += bytes_per_pixel;
	}
	return STP_IMAGE_STATUS_OK;
}
