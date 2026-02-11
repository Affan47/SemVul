ask_question(int qnum)

{
  char *ans;

  qnum--;


  if (question!=NULL)
    writeln(question[qnum]);
  else if (quest_ptr!=NULL)
    print_descr(quest_ptr[qnum],1);
  else {writeln("INT ERR: Invalid question pointer");return 1;}
  ans=agt_readline(2);
  return match_answer(ans,qnum);
}
