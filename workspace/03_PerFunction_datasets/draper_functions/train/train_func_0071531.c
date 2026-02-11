setCurrStreamPosition(le_int32 newPosition)
{
    if (direction < 0) {
        if (newPosition >= prevLimit) {
            position = prevLimit;
            return;
        }

        if (newPosition <= nextLimit) {
            position = nextLimit;
            return;
        }
    } else {
        if (newPosition <= prevLimit) {
            position = prevLimit;
            return;
        }

        if (newPosition >= nextLimit) {
            position = nextLimit;
            return;
        }
    }

    position = newPosition - direction;
    next();
}
