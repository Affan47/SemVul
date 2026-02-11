getdrvid(void)
{ char *p,*p1;

  argp++; argrest--;

  if (argrest < 1)
   { drvid = DEFLECT_ALL_IDS;
     return;
   }

  if ((*argp)[0] == '-')
    drvid = DEFLECT_ALL_IDS;
   else
    { drvid = 0;
      p = *argp;
      while (p)
       { p1 = p;
         p = strchr(p1,'%');
         if (p) *p++ = '\0';
         strcpy(dioctl.getid.drvnam,p1);
         if (ioctl(fd,IIOCGETDRV,&dioctl))
          { fprintf(stderr,"driver %s not found \n",p1);
            close(fd);
            exit(-1);
          }
         drvid |= (1L << dioctl.getid.drvid);
       }
    }
  argp++; argrest--;
}
