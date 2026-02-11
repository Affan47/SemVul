frame_client_gravity(ObFrame *self, gint *x, gint *y)
{

    switch (self->client->gravity) {
    default:
    case NorthWestGravity:
    case SouthWestGravity:
    case WestGravity:
        break;

    case NorthGravity:
    case SouthGravity:
    case CenterGravity:

        *x -= (self->size.right - self->size.left) / 2;
        break;

    case NorthEastGravity:
    case SouthEastGravity:
    case EastGravity:

        *x -= self->size.right + self->size.left -
            self->client->border_width * 2;
        break;

    case ForgetGravity:
    case StaticGravity:

        *x -= self->size.left - self->client->border_width;
        break;
    }


    switch (self->client->gravity) {
    default:
    case NorthWestGravity:
    case NorthEastGravity:
    case NorthGravity:
        break;

    case CenterGravity:
    case EastGravity:
    case WestGravity:

        *y -= (self->size.bottom - self->size.top) / 2;
        break;

    case SouthWestGravity:
    case SouthEastGravity:
    case SouthGravity:

        *y -= self->size.bottom + self->size.top -
            self->client->border_width * 2;
        break;

    case ForgetGravity:
    case StaticGravity:

        *y -= self->size.top - self->client->border_width;
        break;
    }
}
