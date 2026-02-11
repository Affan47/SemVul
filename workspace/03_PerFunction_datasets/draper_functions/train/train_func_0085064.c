checkDeadStress()
{
    Cube::t_models killers = whoIsHeavier(m_model->getPower());

    Cube::t_models::iterator end = killers.end();
    for (Cube::t_models::iterator i = killers.begin(); i != end; ++i) {
        if (!(*i)->rules()->isOnStrongPad((*i)->getWeight())) {
            return true;
        }
    }

    return false;
}
