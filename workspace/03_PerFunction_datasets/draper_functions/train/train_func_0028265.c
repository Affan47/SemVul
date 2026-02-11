output_prefix (void)
{
	int	i;

	if (output_target) {
		for (i = 0; i < output_indent_level; i++) {
			fputc (' ', output_target);
		}
	}
}
