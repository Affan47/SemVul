lxt2_wr_emit_do_breakfile(struct lxt2_wr_trace *lt)
{
unsigned int len = strlen(lt->lxtname);
int i;
char *tname = malloc(len + 30);
FILE *f2, *clone;
off_t cnt, seg;
char buf[32768];

for(i=len;i>0;i--)
	{
	if(lt->lxtname[i]=='.') break;
	}

if(!i)
	{
	sprintf(tname, "%s_%03d.lxt", lt->lxtname, ++lt->break_number);
	}
	else
	{
	memcpy(tname, lt->lxtname, i);
	sprintf(tname+i, "_%03d.lxt", ++lt->break_number);
	}

f2 = fopen(tname, "wb");
if(!f2)
	{
	free(tname);
	return;
	}

clone = fopen(lt->lxtname, "rb");
if(!clone)
	{
	fclose(f2);
	unlink(tname);
	free(tname);
	return;
	}


for(cnt = 0; cnt < lt->break_header_size; cnt += sizeof(buf))
	{
	seg = lt->break_header_size - cnt;
	if(seg > sizeof(buf))
		{
		seg = sizeof(buf);
		}

	if(fread(buf, seg, 1, clone))
		{
		if(!fwrite(buf, seg, 1, f2)) break;
		}
	}

fclose(clone);
fclose(lt->handle);
lt->handle = f2;
free(tname);
}
