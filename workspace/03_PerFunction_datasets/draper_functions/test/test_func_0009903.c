check_int(SIGNED_VALUE num)
{
    if ((SIGNED_VALUE)(int)num != num) {
	rb_out_of_int(num);
    }
}
