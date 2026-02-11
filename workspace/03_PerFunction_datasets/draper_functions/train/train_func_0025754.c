matches_us(faction_value v)
{
 int numvals = 2;
 if (job2 != FACJOB_NULL)
  numvals++;
 for (int i = 0; i < NUM_FACVALS; i++) {
  if (has_value(faction_value(i)))
   numvals++;
 }
 if (has_job(FACJOB_DRUGS) && v == FACVAL_STRAIGHTEDGE)
  return false;
 int avggood = (good / numvals + good) / 2;
 int avgstrength = (strength / numvals + strength) / 2;
 int avgsneak = (sneak / numvals + sneak / 2);
 int avgcrime = (crime / numvals + crime / 2);
 int avgcult = (cult / numvals + cult / 2);


 if ((abs(facval_data[v].good     - avggood)  <= 3 ||
      (avggood >=  5 && facval_data[v].good >=  1) ||
      (avggood <= -5 && facval_data[v].good <=  0))  &&
     (abs(facval_data[v].strength - avgstrength)   <= 5 ||
      (avgstrength >=  5 && facval_data[v].strength >=  3) ||
      (avgstrength <= -5 && facval_data[v].strength <= -1))  &&
     (abs(facval_data[v].sneak    - avgsneak) <= 4 ||
      (avgsneak >=  5 && facval_data[v].sneak >=  1) ||
      (avgsneak <= -5 && facval_data[v].sneak <= -1))  &&
     (abs(facval_data[v].crime    - avgcrime) <= 4 ||
      (avgcrime >=  5 && facval_data[v].crime >=  0) ||
      (avgcrime <= -5 && facval_data[v].crime <= -1))  &&
     (abs(facval_data[v].cult     - avgcult)  <= 3 ||
      (avgcult >=  5 && facval_data[v].cult >=  1) ||
      (avgcult <= -5 && facval_data[v].cult <= -1)))
  return true;
 return false;
}
