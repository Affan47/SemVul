gsicc_nocm_chunky_to_chunky(gx_device *dev, gsicc_link_t *icclink,
                                  gsicc_bufferdesc_t *input_buff_desc,
                                  gsicc_bufferdesc_t *output_buff_desc,
                                  void *inputbuffer, void *outputbuffer)
{
    int k, j;
    byte *inputpos = (byte *) inputbuffer;
    byte *outputpos = (byte *) outputbuffer;
    byte *inputcolor, *outputcolor;
    int num_bytes_in = input_buff_desc->bytes_per_chan;
    int num_bytes_out = output_buff_desc->bytes_per_chan;
    int pixel_in_step = num_bytes_in * input_buff_desc->num_chan;
    int pixel_out_step = num_bytes_out * output_buff_desc->num_chan;


    for (k = 0; k < input_buff_desc->num_rows ; k++) {
        inputcolor = inputpos;
        outputcolor = outputpos;
        for (j = 0; j < input_buff_desc->pixels_per_row; j++) {
            gsicc_nocm_transform_general(dev, icclink, (void*) inputcolor,
                                         (void*) outputcolor, num_bytes_in,
                                          num_bytes_out);
            inputcolor += pixel_in_step;
            outputcolor += pixel_out_step;
        }
        inputpos += input_buff_desc->row_stride;
        outputpos += output_buff_desc->row_stride;
    }
}
