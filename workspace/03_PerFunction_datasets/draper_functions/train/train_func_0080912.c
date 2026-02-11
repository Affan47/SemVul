f_6417(C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_stack_overflow_check;
loop:
t2=C_eqp(t1,C_SCHEME_END_OF_LIST);
if(C_truep(t2)){
return(t2);}
else{
if(C_truep(C_i_pairp(t1))){
t3=t1;
t4=C_u_i_cdr(t3);
t6=t4;
t1=t6;
goto loop;}
else{
return(C_SCHEME_FALSE);}}}
