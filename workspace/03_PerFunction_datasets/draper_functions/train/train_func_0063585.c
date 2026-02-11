end ()
{
    if (infinite)
        return true;
    return mostly_vertical()? steps >= abs(deltay) - 1 : steps >= abs(deltax) - 1;
}
