consoleListJobTotals()
{
   QString cmd("list jobtotals");
   if (mainWin->m_longList) { cmd.prepend("l"); }
   consoleCommand(cmd);
}
