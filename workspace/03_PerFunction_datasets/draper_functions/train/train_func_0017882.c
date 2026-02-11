ptr_diff32(int64_t ptr1, int64_t ptr2)
{
    int32_t ptrid1 = ptr1 >> 32;
    int32_t ptrid2 = ptr2 >> 32;
    if (ptrid1 != ptrid2) {
	(void)bcfail("difference of pointers not pointing to same object!", ptrid1, ptrid2, __FILE__, __LINE__);

	return 0x40000000;
    }
    return (uint32_t)ptr1 - (uint32_t)ptr2;
}
