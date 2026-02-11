DXReadyToRun(Pointer id)
{
    unsigned int signature = 0xEF33AB88;

    if (!id)
	return ERROR;

    if (write(*(int *)id, (char *)&signature, sizeof(int)) == -1)
        return ERROR;

    return OK;
}
