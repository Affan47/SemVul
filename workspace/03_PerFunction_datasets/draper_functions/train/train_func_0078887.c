f_4763(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_stack_overflow_check;
loop:
if(C_truep(C_i_nullp(t1))){
t2=((C_word*)t0)[2];
return(t2);}
else{
t2=C_slot(t1,C_fix(0));
t3=C_slot(t2,C_fix(0));
t4=C_eqp(((C_word*)t0)[3],t3);
if(C_truep(t4)){
return(C_slot(t2,C_fix(1)));}
else{
t5=C_slot(t1,C_fix(1));
t8=t5;
t1=t8;
goto loop;}}}
