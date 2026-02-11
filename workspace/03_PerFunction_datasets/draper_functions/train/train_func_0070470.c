GetLibmeshFaceOrder(int cellType, vtkIdList* libmeshFaceOrder)
{
  libmeshFaceOrder->Initialize();

  switch(cellType)
    {
    case VTK_TETRA:
      libmeshFaceOrder->SetNumberOfIds(4);
      libmeshFaceOrder->SetId(0,1);
      libmeshFaceOrder->SetId(1,2);
      libmeshFaceOrder->SetId(2,3);
      libmeshFaceOrder->SetId(3,0);
      break;
    case VTK_HEXAHEDRON:
      libmeshFaceOrder->SetNumberOfIds(6);
      libmeshFaceOrder->SetId(0,4);
      libmeshFaceOrder->SetId(1,2);
      libmeshFaceOrder->SetId(2,1);
      libmeshFaceOrder->SetId(3,3);
      libmeshFaceOrder->SetId(4,0);
      libmeshFaceOrder->SetId(5,5);
      break;
    case VTK_WEDGE:
      libmeshFaceOrder->SetNumberOfIds(5);
      libmeshFaceOrder->SetId(0,0);
      libmeshFaceOrder->SetId(1,4);
      libmeshFaceOrder->SetId(2,3);
      libmeshFaceOrder->SetId(3,2);
      libmeshFaceOrder->SetId(4,1);
      break;
    case VTK_PYRAMID:
      libmeshFaceOrder->SetNumberOfIds(5);
      libmeshFaceOrder->SetId(0,4);
      libmeshFaceOrder->SetId(1,0);
      libmeshFaceOrder->SetId(2,1);
      libmeshFaceOrder->SetId(3,2);
      libmeshFaceOrder->SetId(4,3);
      break;
    case VTK_QUADRATIC_TETRA:
      libmeshFaceOrder->SetNumberOfIds(4);
      libmeshFaceOrder->SetId(0,1);
      libmeshFaceOrder->SetId(1,2);
      libmeshFaceOrder->SetId(2,3);
      libmeshFaceOrder->SetId(3,0);
      break;
    case VTK_QUADRATIC_HEXAHEDRON:
      libmeshFaceOrder->SetNumberOfIds(6);
      libmeshFaceOrder->SetId(0,4);
      libmeshFaceOrder->SetId(1,2);
      libmeshFaceOrder->SetId(2,1);
      libmeshFaceOrder->SetId(3,3);
      libmeshFaceOrder->SetId(4,0);
      libmeshFaceOrder->SetId(5,5);
      break;
    case VTK_QUADRATIC_WEDGE:
#if VTK_MAJOR_VERSION > 5 || (VTK_MAJOR_VERSION == 5 && VTK_MINOR_VERSION > 0)
    case VTK_BIQUADRATIC_QUADRATIC_WEDGE:
#endif
      libmeshFaceOrder->SetNumberOfIds(5);
      libmeshFaceOrder->SetId(0,0);
      libmeshFaceOrder->SetId(1,4);
      libmeshFaceOrder->SetId(2,3);
      libmeshFaceOrder->SetId(3,2);
      libmeshFaceOrder->SetId(4,1);
      break;
    default:
      cerr<<"Element type not currently supported in libmesh. Skipping element."<<endl;
      break;
    }
}
