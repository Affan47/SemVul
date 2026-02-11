Open(const char *fn,int mode,off_t offs)
{
#ifdef OPEN_DEBUG
   printf("%p->FA::Open(%s,%d)\n",this,fn?fn:"NULL",mode);
#endif
   if(IsOpen())
      Close();
   Resume();
   file.set(fn);
   real_pos=UNKNOWN_POS;
   pos=offs;
   this->mode=mode;
   mkdir_p=false;
   Timeout(0);

   switch((open_mode)mode)
   {
   case STORE:
   case REMOVE:
   case MAKE_DIR:
   case CHANGE_MODE:
      cache->FileChanged(this,file);
      break;
   case REMOVE_DIR:
      cache->FileChanged(this,file);
      cache->TreeChanged(this,file);
      break;
   default:
      break;
   }
}
