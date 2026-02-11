cbf_get_pixel_area (cbf_detector detector, double index1,
                                               double index2,
                                               double *area,
                                               double *projected_area)
{
  double pixel00 [3], pixel01 [3], pixel10 [3], normal [3];

  double length, length00;

  if (!detector)

    return CBF_ARGUMENT;

  if (detector->axes < 2)

    return CBF_NOTIMPLEMENTED;

  cbf_failnez (cbf_get_pixel_coordinates (detector, index1 - 0.5,
                                                    index2 - 0.5,
                                                    &pixel00 [0],
                                                    &pixel00 [1],
                                                    &pixel00 [2]))

  cbf_failnez (cbf_get_pixel_coordinates (detector, index1 - 0.5,
                                                    index2 + 0.5,
                                                    &pixel01 [0],
                                                    &pixel01 [1],
                                                    &pixel01 [2]))

  cbf_failnez (cbf_get_pixel_coordinates (detector, index1 + 0.5,
                                                    index2 - 0.5,
                                                    &pixel10 [0],
                                                    &pixel10 [1],
                                                    &pixel10 [2]))

  pixel01 [0] -= pixel00 [0];
  pixel01 [1] -= pixel00 [1];
  pixel01 [2] -= pixel00 [2];

  pixel10 [0] -= pixel00 [0];
  pixel10 [1] -= pixel00 [1];
  pixel10 [2] -= pixel00 [2];

  normal [0] = pixel01 [1] * pixel10 [2] - pixel10 [1] * pixel01 [2];
  normal [1] = pixel01 [2] * pixel10 [0] - pixel10 [2] * pixel01 [0];
  normal [2] = pixel01 [0] * pixel10 [1] - pixel10 [0] * pixel01 [1];

  length = normal [0] * normal [0] +
           normal [1] * normal [1] +
           normal [2] * normal [2];

  if (length <= 0.0)

    return CBF_UNDEFINED;

  length = sqrt (length);

  if (area)

    *area = length;

  if (projected_area)
  {
    length00 = pixel00 [0] * pixel00 [0] +
               pixel00 [1] * pixel00 [1] +
               pixel00 [2] * pixel00 [2];

    if (length00 <= 0.0)

      return CBF_UNDEFINED;

    length00 = sqrt (length00);

    *projected_area = fabs (pixel00 [0] * normal [0] +
                            pixel00 [1] * normal [1] +
                            pixel00 [2] * normal [2]) / length00;
  }

  return 0;
}
