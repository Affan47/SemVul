DoReadDVDCapacity(JarchSession *session)
{
	unsigned long x;
	int i;

	x = 0;
	for (i=0;i < 32;i++)
		x |= (session->todo->get(TODO_RIPDVD_CAPACITY_DWORD+i) << i);

	session->DVD_capacity = x;
}
