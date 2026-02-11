RecordCombatEvent( const Combat &combat, unsigned char loss1,
                                unsigned char loss2 ) {
  HistEvent *he = new HistEvent;

  he->type = HIST_COMBAT;
  he->data[0] = combat.GetAttacker()->ID();
  he->data[1] = combat.GetDefender()->ID();
  he->data[2] = loss1;
  he->data[3] = loss2;

  events.AddTail( he );
  return 0;
}
