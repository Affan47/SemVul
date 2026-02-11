P_ActivateInStasisCeiling(line_t * line)
{
    int i;

    for (i = 0; i < MAXCEILINGS; i++)
        if (activeceilings[i] && (activeceilings[i]->tag == line->tag) &&
            (activeceilings[i]->direction == 0))
        {
            activeceilings[i]->direction = activeceilings[i]->olddirection;
            activeceilings[i]->thinker.function = T_MoveCeiling;
        }
}
