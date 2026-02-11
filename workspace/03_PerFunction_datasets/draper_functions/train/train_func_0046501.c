checkDead(Cube::eAction lastAction)
{

    bool dead = false;

    if (m_model->isAlive()) {
        switch (lastAction) {
            case Cube::ACTION_FALL:
                dead = checkDeadFall();
                break;
            case Cube::ACTION_MOVE:
                dead = checkDeadMove();
                break;
            default:
                dead = false;
                break;
        }

        if (!dead) {
            dead = checkDeadStress();
        }

        if (dead) {
            m_readyToDie = true;
        }
    }

    return dead;
}
