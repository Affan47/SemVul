input_ln FCN((p0))
INPUT_PRMS0 HUGE*p0 C1("Which structure describes the current file?")
{
cur0_prms= p0;
limit= cur_buffer;


cur_line++;


if(!nuweb_mode&&FORTRAN_LIKE(language)&&column_mode&&parsing_mode==OUTER)
switch(language)
{
case FORTRAN:
case FORTRAN_90:
if(!rd_Fortran())
return NO;
break;

case RATFOR:
case RATFOR_90:
if(!rd_Ratfor())
return NO;

if(limit==cur_buffer)
goto empty_line;
break;

default:

confusion(OC("input_ln"),OC("Invalid FORTRAN_LIKE language %i"),language);
}
else
if(!rd_free_form())
return NO;


if(column_mode&&FORTRAN_LIKE(language)&&
PTR_DIFF(size_t,limit,cur_buffer)==2&&
((!auto_semi&&(cur_buffer[1]==';'||cur_buffer[1]==' '))||
(auto_semi&&cur_buffer[1]==';'&&(cur_buffer[0]=='C'||
cur_buffer[0]=='c'||cur_buffer[0]=='*'))))
empty_line:
limit= cur_buffer;


#line 746 "./common.web"

#if(DEBUG)

#line 768 "./common.web"

{
register ASCII HUGE*k;

if(prn_input_lines&&cur_line>=(LINE_NUMBER)start_line
&&cur_line<(LINE_NUMBER)end_line)
{
if(prn_input_addresses)
printf("%lu->%lu (%u) ",
(unsigned long)cur_buffer,(unsigned long)limit,
PTR_DIFF(unsigned,limit,cur_buffer));

printf("%c[%d%s:%u]: \"",
(language==global_language?' ':*LANGUAGE_CODE(language)),
incl_depth,
(changing?"*":""),
cur_line);

for(k= cur_buffer;k<limit;++k)
switch(*k)
{
case(ASCII)begin_comment0:
printf("</*>");
break;

case(ASCII)begin_comment1:
printf("<//>");
break;

case interior_semi:
printf("<;>");
break;

default:
putchar(XCHR(*k));
break;
}

puts("\"");
}
}


#line 748 "./common.web"
;
#endif

return YES;
}
