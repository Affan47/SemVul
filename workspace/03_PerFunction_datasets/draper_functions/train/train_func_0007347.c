non_ui_ctrlc(int foo)
{
if(tunetime.min==0 && tunetime.sec==0 &&
   tunetime.subsecframes<25)
  playing=0;
else
  need_nexttrack=1;
}
