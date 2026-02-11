insertp(int i)
{
    outArray[outarray_size]=i;
    if (outarray_size<max_output_size)
        outarray_size ++;
    else
    {
        printf("outSourceArray length is out of bounds. Please contact code writer.\n");
        printf("   outarray_size = %d, max_output_size = %d\n",outarray_size,max_output_size);
        exit(1);
    }
}
