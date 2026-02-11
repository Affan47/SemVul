getPerspectiveProjectionParameters(
    float& left,
    float& right,
    float& bottom,
    float& top,
    float& nearval,
    float& farval,
    float upDirection) const {

    debugAssertM(abs(upDirection) == 1.0f, "upDirection must be -1 or +1");

    float x = elt[0][0];
    float y = elt[1][1] * upDirection;
    float a = elt[0][2];
    float b = elt[1][2] * upDirection;
    float c = elt[2][2];
    float d = elt[2][3];


    debugAssertM(elt[3][2] == -1, "Not a projection matrix");
    debugAssertM(elt[0][1] == 0, "Not a projection matrix");
    debugAssertM(elt[0][3] == 0, "Not a projection matrix");
    debugAssertM(elt[1][3] == 0, "Not a projection matrix");
    debugAssertM(elt[3][3] == 0, "Not a projection matrix");
    debugAssertM(elt[1][0] == 0, "Not a projection matrix");
    debugAssertM(elt[2][0] == 0, "Not a projection matrix");
    debugAssertM(elt[2][1] == 0, "Not a projection matrix");
    debugAssertM(elt[3][0] == 0, "Not a projection matrix");
    debugAssertM(elt[3][1] == 0, "Not a projection matrix");

    if (c == -1) {
        farval = finf();
        nearval = -d / 2.0f;
    } else {
        nearval = d * ((c - 1.0f) / (c + 1.0f) - 1.0f) / (-2.0f * (c - 1.0f) / (c + 1.0f));
        farval = nearval * ((c - 1.0f) / (c + 1.0f));
    }


    left = (a - 1.0f) * nearval / x;
    right = 2.0f * nearval / x + left;

    bottom = (b - 1.0f) * nearval / y;
    top = 2.0f * nearval / y + bottom;
}
