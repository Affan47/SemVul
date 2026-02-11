arm_mac_accumulator_is_result (rtx producer, rtx consumer)
{
  rtx result;
  rtx op0, op1, acc;

  producer = PATTERN (producer);
  consumer = PATTERN (consumer);

  if (GET_CODE (producer) == COND_EXEC)
    producer = COND_EXEC_CODE (producer);
  if (GET_CODE (consumer) == COND_EXEC)
    consumer = COND_EXEC_CODE (consumer);

  if (GET_CODE (producer) != SET)
    return 0;

  result = XEXP (producer, 0);

  if (GET_CODE (consumer) != SET)
    return 0;


  if (GET_CODE (XEXP (consumer, 1)) == PLUS)
    {
      if (GET_CODE (XEXP (XEXP (consumer, 1), 0)) != MULT)
        return 0;

      op0 = XEXP (XEXP (XEXP (consumer, 1), 0), 0);
      op1 = XEXP (XEXP (XEXP (consumer, 1), 0), 1);
      acc = XEXP (XEXP (consumer, 1), 1);
    }
  else if (GET_CODE (XEXP (consumer, 1)) == MINUS)
    {
      if (GET_CODE (XEXP (XEXP (consumer, 1), 1)) != MULT)
        return 0;

      op0 = XEXP (XEXP (XEXP (consumer, 1), 1), 0);
      op1 = XEXP (XEXP (XEXP (consumer, 1), 1), 1);
      acc = XEXP (XEXP (consumer, 1), 0);
    }
  else
    return 0;

  return (reg_overlap_mentioned_p (result, acc)
          && !reg_overlap_mentioned_p (result, op0)
          && !reg_overlap_mentioned_p (result, op1));
}
