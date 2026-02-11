Read (FILE *file,DBInt swap)
			{
			int i;
			if (fread (this,sizeof (ARCDirRecord),1,file) != 1) return (DBFault);
			for (i = sizeof (InternalName) - 1;i >= 0;--i)
				InternalName [i] = InternalName [i] == ' ' ? '\0' : tolower (InternalName [i]);
			for (i = sizeof (ExternalName) - 1;i >= 0;--i)
				ExternalName [i] = ExternalName [i] == ' ' ? '\0' : tolower (ExternalName [i]);
			if (swap) Swap ();
			return (DBSuccess);
			}
