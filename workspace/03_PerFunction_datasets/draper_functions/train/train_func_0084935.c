Adapt_buffer_convert(dc1394video_frame_t *in, dc1394video_frame_t *out)
{
    uint32_t bpp;


    out->size[0]=in->size[0];
    out->size[1]=in->size[1];
    out->position[0]=in->position[0];
    out->position[1]=in->position[1];


    out->color_filter=in->color_filter;


    out->data_depth=8;


    out->video_mode = in->video_mode;


    out->padding_bytes = in->padding_bytes;


    dc1394_get_color_coding_bit_size(out->color_coding, &bpp);
    out->image_bytes=(out->size[0]*out->size[1]*bpp)/8;


    out->total_bytes = out->image_bytes + out->padding_bytes;


    out->packet_size  = in->packet_size;
    out->packets_per_frame = in->packets_per_frame;


    out->timestamp = in->timestamp;
    out->frames_behind = in->frames_behind;
    out->camera = in->camera;
    out->id = in->id;


    if (out->total_bytes>out->allocated_image_bytes) {
        free(out->image);
        out->image=(uint8_t*)malloc(out->total_bytes*sizeof(uint8_t));
        if (out->image)
            out->allocated_image_bytes = out->total_bytes*sizeof(uint8_t);
        else
            out->allocated_image_bytes = 0;
    }


    if(out->image)
        memcpy(&(out->image[out->image_bytes]),&(in->image[in->image_bytes]),out->padding_bytes);

    out->little_endian=0;
    out->data_in_padding=0;

    if(out->image)
        return DC1394_SUCCESS;

    return DC1394_MEMORY_ALLOCATION_FAILURE;
}
