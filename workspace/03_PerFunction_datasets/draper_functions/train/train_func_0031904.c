ANTSUseLandmarkImagesToGetAffineTransform( std::vector<std::string> args, std::ostream* )
{


  args.insert( args.begin(), "ANTSUseLandmarkImagesToGetAffineTransform" );
  int     argc = args.size();
  char* * argv = new char *[args.size() + 1];
  for( unsigned int i = 0; i < args.size(); ++i )
    {

    argv[i] = new char[args[i].length() + 1];
    std::strncpy( argv[i], args[i].c_str(), args[i].length() );

    argv[i][args[i].length()] = '\0';
    }
  argv[argc] = 0;

  class Cleanup_argv
  {
public:
    Cleanup_argv( char* * argv_, int argc_plus_one_ ) : argv( argv_ ), argc_plus_one( argc_plus_one_ )
    {
    }

    ~Cleanup_argv()
    {
      for( unsigned int i = 0; i < argc_plus_one; ++i )
        {
        delete[] argv[i];
        }
      delete[] argv;
    }

private:
    char* *      argv;
    unsigned int argc_plus_one;
  };
  Cleanup_argv cleanup_argv( argv, argc + 1 );


  if( argc < 3 )
    {
    std::cout << "Usage:   " << argv[0]
             <<
      " FixedImageWithLabeledLandmarks.nii.gz  MovingImageWithLabeledLandmarks.nii.gz [rigid | affine] OutAffine.txt "
             << std::endl;
    std::cout
      << " we expect the input images to be (1) N-ary  (2) in the same physical space as the images you want to "
      << std::endl;
    std::cout << " register and (3 ) to have the same landmark points defined within them ... " << std::endl;
    std::cout << " landmarks will be defined from the center of mass of the labels in the input images . " << std::endl;
    std::cout << " You can use ITK-snap to generate the label images. " << std::endl;
    if( argc >= 2 &&
        ( std::string( argv[1] ) == std::string("--help") || std::string( argv[1] ) == std::string("-h") ) )
      {
      return EXIT_SUCCESS;
      }
    return EXIT_FAILURE;
    }


  std::string               fn = std::string(argv[1]);
  itk::ImageIOBase::Pointer imageIO =
    itk::ImageIOFactory::CreateImageIO(fn.c_str(), itk::ImageIOFactory::ReadMode);
  imageIO->SetFileName(fn.c_str() );
  imageIO->ReadImageInformation();

  switch( imageIO->GetNumberOfDimensions() )
    {
    case 2:
      {
      LandmarkBasedTransformInitializer2D(argc, argv);
      }
      break;
    case 3:
      {
      LandmarkBasedTransformInitializer3D(argc, argv);
      }
      break;
    default:
      std::cerr << "Unsupported dimension" << std::endl;
      exit( EXIT_FAILURE );
    }
  return EXIT_SUCCESS;
}
