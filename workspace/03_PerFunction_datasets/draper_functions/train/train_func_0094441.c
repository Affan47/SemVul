view_init()
{
    int i;

    for (i = 0; i < CLOSE_MAX_BC_DY; i++)
	close_dy[i] = &close_table[i];

    for (i = 0; i < FAR_MAX_BC_DY; i++)
	far_dy[i] = &far_table[i];
}
