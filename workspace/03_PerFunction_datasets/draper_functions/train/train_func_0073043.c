gx_device_forward_color_procs(gx_device_forward * dev)
{
    set_dev_proc(dev, map_rgb_color, gx_forward_map_rgb_color);
    set_dev_proc(dev, map_color_rgb, gx_forward_map_color_rgb);
    set_dev_proc(dev, map_cmyk_color, gx_forward_map_cmyk_color);
    set_dev_proc(dev, map_rgb_alpha_color, gx_forward_map_rgb_alpha_color);
    set_dev_proc(dev, get_color_mapping_procs, gx_forward_get_color_mapping_procs);
    set_dev_proc(dev, get_color_comp_index, gx_forward_get_color_comp_index);
    set_dev_proc(dev, encode_color, gx_forward_encode_color);
    set_dev_proc(dev, decode_color, gx_forward_decode_color);
    set_dev_proc(dev, get_profile, gx_forward_get_profile);

    fill_dev_proc(dev, set_graphics_type_tag, gx_forward_set_graphics_type_tag);
    fill_dev_proc(dev, dev_spec_op, gx_forward_dev_spec_op);
}
