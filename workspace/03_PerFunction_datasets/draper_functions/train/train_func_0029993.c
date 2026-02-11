torch_Timer_stop(lua_State *L)
{
  Timer *timer = luaT_checkudata(L, 1, torch_Timer_id);
  if(timer->isRunning)
  {
    double currentTime = torch_Timer_runTime() - timer->startTime;
    timer->totalTime += currentTime;
    timer->isRunning = 0;
  }
  lua_settop(L, 1);
  return 1;
}
