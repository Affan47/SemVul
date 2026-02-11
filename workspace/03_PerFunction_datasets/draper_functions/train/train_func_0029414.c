difficultyLevelToInt()
{

    for (int i = 0; i < Kg::difficulty()->levels().size(); i++)
        if (Kg::difficultyLevel()
                == Kg::difficulty()->levels()[i]->standardLevel())
            return i;

    return -1;
}
