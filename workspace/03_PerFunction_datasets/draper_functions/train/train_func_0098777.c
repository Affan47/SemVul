opinion_text()
{
 std::stringstream ret;
 if (op_of_u.trust <= -10)
  ret << "Completely untrusting";
 else if (op_of_u.trust <= -6)
  ret << "Very untrusting";
 else if (op_of_u.trust <= -3)
  ret << "Untrusting";
 else if (op_of_u.trust <= 2)
  ret << "Uneasy";
 else if (op_of_u.trust <= 5)
  ret << "Trusting";
 else if (op_of_u.trust < 10)
  ret << "Very trusting";
 else
  ret << "Completely trusting";

 ret << " (Trust " << op_of_u.trust << "); ";

 if (op_of_u.fear <= -10)
  ret << "Thinks you're laughably harmless";
 else if (op_of_u.fear <= -6)
  ret << "Thinks you're harmless";
 else if (op_of_u.fear <= -3)
  ret << "Unafraid";
 else if (op_of_u.fear <= 2)
  ret << "Wary";
 else if (op_of_u.fear <= 5)
  ret << "Afraid";
 else if (op_of_u.fear < 10)
  ret << "Very afraid";
 else
  ret << "Terrified";

 ret << " (Fear " << op_of_u.fear << "); ";

 if (op_of_u.value <= -10)
  ret << "Considers you a major liability";
 else if (op_of_u.value <= -6)
  ret << "Considers you a burden";
 else if (op_of_u.value <= -3)
  ret << "Considers you an annoyance";
 else if (op_of_u.value <= 2)
  ret << "Doesn't care about you";
 else if (op_of_u.value <= 5)
  ret << "Values your presence";
 else if (op_of_u.value < 10)
  ret << "Treasures you";
 else
  ret << "Best Friends Forever!";

 ret << " (Value " << op_of_u.value << "); ";

 if (op_of_u.anger <= -10)
  ret << "You can do no wrong!";
 else if (op_of_u.anger <= -6)
  ret << "You're good people";
 else if (op_of_u.anger <= -3)
  ret << "Thinks well of you";
 else if (op_of_u.anger <= 2)
  ret << "Ambivalent";
 else if (op_of_u.anger <= 5)
  ret << "Pissed off";
 else if (op_of_u.anger < 10)
  ret << "Angry";
 else
  ret << "About to kill you";

 ret << " (Anger " << op_of_u.anger << ")";

 return ret.str();
}
