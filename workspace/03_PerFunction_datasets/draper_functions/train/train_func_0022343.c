__ecereNameSpace__ecere__sys__Sleep(double seconds)
{
if(!seconds)
sched_yield();
else
{
struct timeval tv =
{
(int)(double)seconds, ((double)(double)((seconds - (double)(int)(double)seconds) * (double)1000000))
};

select(0, (((void *)0)), (((void *)0)), (((void *)0)), &tv);
}
}
