frz_params(VOID)
{


#line 6489 "./common.web"

cont_char= XORD(in_escape);
free_90= BOOLEAN(Fortran88&&free_form_input);
free_Fortran= BOOLEAN((language==FORTRAN_90)&&free_90);

if(!prn_semis&&free_Fortran&&auto_pseudo_semis)
prn_semis= YES;


#line 6502 "./common.web"

if(program==tangle&&free_90)
switch(language)
{
case FORTRAN_90:
case RATFOR_90:
begin_comment_char[lan_num(FORTRAN_90)]=
(outer_char)CHOICE(free_90,'!','C');
break;

default:;
}

}
