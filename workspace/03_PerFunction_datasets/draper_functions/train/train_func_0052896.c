check_font(void)
{
    if (global_color != current_fontcolor || (global_font && default_font)) {
	fprintf(output_file, "\\bgroup");
	if (global_color != current_fontcolor) {
	    fprintf(output_file, "\\%s", color_string(global_color));
	    current_fontcolor = global_color;
	}
	if (global_font && default_font) {
	    fprintf(output_file, "\\%s", global_font_desc);
	    default_font = 0;
	}
	putc('\n', output_file);
    }
}
