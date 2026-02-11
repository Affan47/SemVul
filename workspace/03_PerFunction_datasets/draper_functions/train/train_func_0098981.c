f_2503(C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_stack_overflow_check;
loop:
t2=C_i_cdr(t1);
if(C_truep(C_i_pairp(t2))){
t5=t2;
t1=t5;
goto loop;}
else{
t3=t1;
return(t3);}}
