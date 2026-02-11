stepBy(int steps)
{
    double increaseValue = (steps > 0)?(steps-.5):(steps+.49999);
    double oldValue = m_originalValue;
    double newValue = qRound(oldValue + increaseValue);

    if (newValue < 1)
        return;

    setValue(newValue);
    emit(valueEdited(value()));
}
