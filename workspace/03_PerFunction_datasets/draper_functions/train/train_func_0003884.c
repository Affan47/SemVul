GetPacketTypeText()
{
   struct code_text text_table[]={
      { SSH_FXP_INIT,          "INIT"		},
      { SSH_FXP_VERSION,       "VERSION"	},
      { SSH_FXP_OPEN,          "OPEN"		},
      { SSH_FXP_CLOSE,         "CLOSE"		},
      { SSH_FXP_READ,          "READ"		},
      { SSH_FXP_WRITE,         "WRITE"		},
      { SSH_FXP_LSTAT,         "LSTAT"		},
      { SSH_FXP_FSTAT,         "FSTAT"		},
      { SSH_FXP_SETSTAT,       "SETSTAT"	},
      { SSH_FXP_FSETSTAT,      "FSETSTAT"	},
      { SSH_FXP_OPENDIR,       "OPENDIR"	},
      { SSH_FXP_READDIR,       "READDIR"	},
      { SSH_FXP_REMOVE,        "REMOVE"		},
      { SSH_FXP_MKDIR,         "MKDIR"		},
      { SSH_FXP_RMDIR,         "RMDIR"		},
      { SSH_FXP_REALPATH,      "REALPATH"	},
      { SSH_FXP_STAT,          "STAT"		},
      { SSH_FXP_RENAME,        "RENAME"		},
      { SSH_FXP_READLINK,      "READLINK"	},
      { SSH_FXP_SYMLINK,       "SYMLINK"	},
      { SSH_FXP_LINK,          "LINK"		},
      { SSH_FXP_BLOCK,         "BLOCK"		},
      { SSH_FXP_UNBLOCK,       "UNBLOCK"	},
      { SSH_FXP_STATUS,        "STATUS"		},
      { SSH_FXP_HANDLE,        "HANDLE"		},
      { SSH_FXP_DATA,          "DATA"		},
      { SSH_FXP_NAME,          "NAME"		},
      { SSH_FXP_ATTRS,         "ATTRS"		},
      { SSH_FXP_EXTENDED,      "EXTENDED"	},
      { SSH_FXP_EXTENDED_REPLY,"EXTENDED_REPLY"	},
      {0,0}
   };
   for(int i=0; text_table[i].text; i++)
      if(text_table[i].code==type)
	 return text_table[i].text;
   return "UNKNOWN";
}
