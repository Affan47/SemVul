f_2328(C_word t0,C_word t1){
C_word tmp;
C_word t2;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_stack_overflow_check;
loop:
if(C_truep(C_fixnum_greater_or_equal_p(t1,((C_word*)t0)[2]))){
t2=((C_word*)t0)[3];
return(t2);}
else{
t2=C_slot(((C_word*)t0)[4],t1);
t3=C_i_setslot(((C_word*)t0)[3],t1,t2);
t4=C_fixnum_plus(t1,C_fix(1));
t7=t4;
t1=t7;
goto loop;}}
