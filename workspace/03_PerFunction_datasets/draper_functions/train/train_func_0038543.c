writeHatchEdge(DL_WriterA& dw,
                            const DL_HatchEdgeData& data) {

    dw.dxfInt(72, data.type);

    switch (data.type) {
    case 1:
        dw.dxfReal(10, data.x1);
        dw.dxfReal(20, data.y1);
        dw.dxfReal(11, data.x2);
        dw.dxfReal(21, data.y2);
        break;
    case 2:
        dw.dxfReal(10, data.cx);
        dw.dxfReal(20, data.cy);
        dw.dxfReal(40, data.radius);
        dw.dxfReal(50, data.angle1/(2*M_PI)*360.0);
        dw.dxfReal(51, data.angle2/(2*M_PI)*360.0);
        dw.dxfInt(73, (int)(data.ccw));
        break;
    default:
        break;
    }
}
