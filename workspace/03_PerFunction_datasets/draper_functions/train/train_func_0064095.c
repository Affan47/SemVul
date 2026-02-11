f_2908(C_word t0,C_word t1,C_word t2){
C_word tmp;
C_word t3;
C_word t4;
C_word t5;
C_word t6;
C_word t7;
C_word t8;
C_word t9;
C_word t10;
C_word t11;
C_word t12;
C_word t13;
C_word t14;
C_stack_overflow_check;
loop:
if(C_truep(C_i_pairp(t2))){
t3=t2;
t4=C_u_i_car(t3);
t5=t2;
t6=C_u_i_cdr(t5);
t7=C_i_string_length(t4);
t8=C_fixnum_difference(t1,t7);
t9=((C_word*)t0)[2];
t10=C_substring_copy(t4,t9,C_fix(0),t7,t8);
t13=t8;
t14=t6;
t1=t13;
t2=t14;
goto loop;}
else{
t3=C_SCHEME_UNDEFINED;
return(t3);}}
