my_CriticalSections_Multi()
{
	randomGenerator.randomize();

	for (int i=1;i<=10;i++)
		createThread( thread_example, i );


	int cnt;
	do
	{
		sleep(10);
		csCounter.enter();
		cnt = counter;
		csCounter.leave();
	} while (cnt);
}
