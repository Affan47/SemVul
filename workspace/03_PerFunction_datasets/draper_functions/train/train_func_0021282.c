SetMountPath (char *value)

{ char buff[CF_EXPANDSIZE];

ExpandVarstring(value,buff,"");

Debug("Appending [%s] to mountlist\n",buff);

AppendItem(&VMOUNTLIST,buff,CLASSBUFF);
}
