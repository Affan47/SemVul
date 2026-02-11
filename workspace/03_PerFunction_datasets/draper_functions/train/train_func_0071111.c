CheckOldLock()

{ time_t mtime;

Debug("CheckOldLock(%s)\n",CFLOCK);

if ((mtime = GetLockTime(CFLOCK)) == -1)
   {
   Debug("Unable to find lock data %s\n",CFLOCK);
   return 0;
   }
else
   {
   Debug("Lock %s last ran at %s\n",CFLOCK,ctime(&mtime));
   return mtime;
   }
}
